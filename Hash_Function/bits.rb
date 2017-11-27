# Module handling bits conversion and comparing
module Bits
  # Fix sizes of bits in strings
  def fix_size(string, lengthFix)
    fixedString = ''
    # Add 0 to the string to match bigger size
    lengthFix.times do
      fixedString << '0'
    end
    # Append string with old one
    fixedString << string
    return fixedString
  end
  # Count the number of bits in hash
  def fix(first, second, size)
    first = fix_size(first, size - first.length) if first.length < size
    second = fix_size(second, size - second.length) if second.length < size
    return first.length, first, second
  end

  # Count the difference
  def count_difference(first, second, size)
    # First change hex to integer and than to bits
    first  = first.to_i(16).to_s(2)
    second = second.to_i(16).to_s(2)
    # Fix if string don't match size
    numberOfBits, first, second = fix(first, second, size)
    # Start counting the difference
    counter = 0
    first.length.times do |c|
      counter += 1 if first[c] != second[c]
    end
    # Calculate precentege of difference in precentege format
    precentegeDiff = ((counter.to_f / numberOfBits.to_f).round(2) * 100).to_i
    return counter, precentegeDiff, numberOfBits
  end

  module_function :count_difference, :fix, :fix_size
end
# Run bash script with hash functions
system("./hash.sh")
# Open the file with results
helpFile = File.read('hash.txt')
helpFile.gsub!(/\r\n?/, "\n")
# Table with all hash keys
table = []
# Read string from each line
helpFile.each_line do |line|
  # Delete unwanted chars from string
  line = line[0...-4]
  # In case if strings are not ended in "   -" way
  # line.chomp!
  # Add formated hash to table
  table << line
end
# Open file to output the results
outputFile = File.open('diff.txt', 'w+')
  # Count the difference in bits of two keys for:
  # md5sum
  counter, precentegeDiff, numberOfBits = Bits::count_difference(table[0], table[1], 128)
  outputFile.puts('Wyniki dla md5sum:')
  outputFile.puts table[0]
  outputFile.puts table[1]
  outputFile.puts("Liczba różnych bitów: #{counter} czyli #{precentegeDiff}% z #{numberOfBits} bitów\n\n")
  # sha1sum
  counter, precentegeDiff, numberOfBits = Bits::count_difference(table[2], table[3], 160)
  outputFile.puts('Wyniki dla sha1sum:')
  outputFile.puts table[2]
  outputFile.puts table[3]
  outputFile.puts("Liczba różnych bitów: #{counter} czyli #{precentegeDiff}% z #{numberOfBits} bitów\n\n")
  # sha224sum
  counter, precentegeDiff, numberOfBits = Bits::count_difference(table[4], table[5], 224)
  outputFile.puts('Wyniki dla sha224sum:')
  outputFile.puts table[4]
  outputFile.puts table[5]
  outputFile.puts("Liczba różnych bitów: #{counter} czyli #{precentegeDiff}% z #{numberOfBits} bitów\n\n")
  # sha256sum
  counter, precentegeDiff, numberOfBits = Bits::count_difference(table[6], table[7], 256)
  outputFile.puts('Wyniki dla sha256sum:')
  outputFile.puts table[6]
  outputFile.puts table[7]
  outputFile.puts("Liczba różnych bitów: #{counter} czyli #{precentegeDiff}% z #{numberOfBits} bitów\n\n")
  # sha384sum
  counter, precentegeDiff, numberOfBits = Bits::count_difference(table[8], table[9], 384)
  outputFile.puts('Wyniki dla sha384sum:')
  outputFile.puts table[8]
  outputFile.puts table[9]
  outputFile.puts("Liczba różnych bitów: #{counter} czyli #{precentegeDiff}% z #{numberOfBits} bitów\n\n")
  # sha512sum
  counter, precentegeDiff, numberOfBits = Bits::count_difference(table[10], table[11], 512)
  outputFile.puts('Wyniki dla sha512sum:')
  outputFile.puts table[10]
  outputFile.puts table[11]
  outputFile.puts("Liczba różnych bitów: #{counter} czyli #{precentegeDiff}% z #{numberOfBits} bitów\n\n")
outputFile.close
