require_relative 'bmp_lib.rb'
require 'openssl'

# Patch for string class to make pretty hex string from ASCII-ugly string
class String
  def to_hex
    string = ''
    # string += "0x"
    self.each_char { |chr| string += chr.ord.to_s(16) }
    string
  end
end
# Cipher class includes encryption methods
class Cipher
  # Encryption methods
  class Encryption
    def initialize(array_of_pixels, widthNew, heightNew)
      @pix = array_of_pixels
      @widthNew = widthNew
      @heightNew = heightNew
    end

    def encryptECB
      # I choose the sha384, 'cause each pixel is 6 chars
      # Example hash for string
      # 0x24108e0476474605ef4b186369866d575fe072...
      # will always cover 4x3 block = 12 blocks 'cause hash varry from 91 to 94

      # Initialize hashing function
      sha384 = OpenSSL::Digest::SHA384.new
      # Initialize output bmp file with same properties as plain
      bmp = BMP::Writer.new(@widthNew, @heightNew)
      # These two are for iteration over the bmp file "array"
      i = 0
      k = 0

      while k < @heightNew
        while i < @widthNew
          # Read 4x3block, 12 pixels from given array and encrypt them
          # reset string on each block
          str = ''
          str += @pix[i, k]
          str += @pix[i, k + 1]
          str += @pix[i, k + 2]

          str += @pix[i + 1, k]
          str += @pix[i + 1, k + 1]
          str += @pix[i + 1, k + 2]

          str += @pix[i + 2, k]
          str += @pix[i + 2, k + 1]
          str += @pix[i + 2, k + 2]

          str += @pix[i + 3, k]
          str += @pix[i + 3, k + 1]
          str += @pix[i + 3, k + 2]

          str = str.to_hex
          str = sha384.digest(str)
          str = str.to_hex

          # Take only 72 needed chars
          str = str[0..71]
          # Slice it into 6 char blocks array
          str = str.scan(/.{1,6}/)

          # Make changes in pixels array
          bmp[i, k] = str[0]
          bmp[i, k + 1] = str[1]
          bmp[i, k + 2] = str[2]

          bmp[i + 1, k]     = str[3]
          bmp[i + 1, k + 1] = str[4]
          bmp[i + 1, k + 2] = str[5]

          bmp[i + 2, k] = str[6]
          bmp[i + 2, k + 1] = str[7]
          bmp[i + 2, k + 2] = str[8]

          bmp[i + 3, k] = str[9]
          bmp[i + 3, k + 1] = str[10]
          bmp[i + 3, k + 2] = str[11]

          # reset sha hash function
          sha384.reset
          # increment i to go to next block
          i += 4
        end
        # increment k to go to next line of blocks and rollback with i
        k += 3
        i = 0
      end
      # Save the result in ecb_crypto.bmp
      bmp.save_as('ecb_crypto.bmp')
    end

    def xorBlocks(plainBlock, lastBlock)
      # String is an array for init
      string = []
      # Scan blocks into hex values
      plainBlock = plainBlock.scan(/.{1,2}/)
      lastBlock  = lastBlock.scan(/.{1,2}/)
      # Iterate over array of 2 blocks
      (0...3).each do |c|
        string << ((plainBlock[c]).hex ^ (lastBlock[c]).hex).to_s(16)
      end
      string = string.join('')
      # return string
    end

    def encryptCBC
      # Tmp array for last block, so we can xor it with new on
      tmp = []
      # Initialization vector for first iteration
      tmp[0] = '030f0f'
      tmp[1] = 'ff0f0f'
      tmp[2] = '0fff0f'
      tmp[3] = '0f110f'
      tmp[4] = '0f330f'
      tmp[5] = '0fff0f'
      tmp[6] = '0fff0f'
      tmp[7] = '0faa0f'
      tmp[8] = '0aaf0f'
      tmp[9] = '011f0f'
      tmp[10] = '0f990f'
      tmp[11] = '012f0f'
      # Initialize hashing function
      sha384 = OpenSSL::Digest::SHA384.new
      # Initialize output bmp file with same properties as plain
      bmp = BMP::Writer.new(@widthNew, @heightNew)
      # These two are for iteration over the bmp file "array"
      i = 0
      k = 0

      while k < @heightNew
        while i < @widthNew
          # Read 4x3block, 12 pixels from given array and
          # xor them with last used block, reset string on each block
          str = ''

          str += xorBlocks(@pix[i, k], tmp[0])
          str += xorBlocks(@pix[i, k + 1], tmp[1])
          str += xorBlocks(@pix[i, k + 2], tmp[2])

          str += xorBlocks(@pix[i + 1, k], tmp[3])
          str += xorBlocks(@pix[i + 1, k + 1], tmp[4])
          str += xorBlocks(@pix[i + 1, k + 2], tmp[5])

          str += xorBlocks(@pix[i + 2, k], tmp[6])
          str += xorBlocks(@pix[i + 2, k + 1], tmp[7])
          str += xorBlocks(@pix[i + 2, k + 2], tmp[8])

          str += xorBlocks(@pix[i + 3, k], tmp[9])
          str += xorBlocks(@pix[i + 3, k + 1], tmp[10])
          str += xorBlocks(@pix[i + 3, k + 2], tmp[11])

          str = str.to_hex
          str = sha384.digest(str)
          str = str.to_hex

          # Take only 72 needed chars
          str = str[0..71]
          # Slice it into 6 char blocks array
          str = str.scan(/.{1,6}/)

          # Make changes in pixels array
          # And make new tmp array with last used block
          bmp[i, k] = tmp[0] = str[0]
          bmp[i, k + 1] = tmp[1] = str[1]
          bmp[i, k + 2] = tmp[2] = str[2]

          bmp[i + 1, k] = tmp[3] = str[3]
          bmp[i + 1, k + 1] = tmp[4] = str[4]
          bmp[i + 1, k + 2] = tmp[5] = str[5]

          bmp[i + 2, k]     = tmp[6] = str[6]
          bmp[i + 2, k + 1] = tmp[7] = str[7]
          bmp[i + 2, k + 2] = tmp[8] = str[8]

          bmp[i + 3, k] = tmp[9] = str[9]
          bmp[i + 3, k + 1] = tmp[10] = str[10]
          bmp[i + 3, k + 2] = tmp[11] = str[11]

          # reset sha hash function
          sha384.reset
          # increment i to go to next block
          i += 4
        end
        # increment k to go to next line of blocks and rollback with i
        k += 3
        i = 0
      end
      # Save the result in cbc_crypto.bmp
      bmp.save_as('cbc_crypto.bmp')
    end
  end
end

####################
### Main program ###
####################

# Read bmp file from plain.bmp into array of pixels
plain   = BMP::Reader.new('plain.bmp')
encrypt = Cipher::Encryption.new(plain, plain.width, plain.height)

# Shows the size of bmp file in pixels
puts "Szerokość bitmapy : #{plain.width}px"
puts "Wysokość bitmapy  : #{plain.height}px"
# puts plain[szerokosc, wysokosc]

# Transform blocks of pixels with selected encryption method
encrypt.encryptECB
encrypt.encryptCBC
