#!/bin/bash
if [ -e hash.pdf ] ; then
  if [ -e hash.txt ] ; then
    rm hash.txt
  else
    touch hash.txt
  fi
  # md5sum
  cat hash.pdf personal.txt | md5sum >> hash.txt
  cat hash.pdf personal_.txt | md5sum >> hash.txt
  # sha1sum
  cat hash.pdf personal.txt | sha1sum >> hash.txt
  cat hash.pdf personal_.txt | sha1sum >> hash.txt
  # sha224sum
  cat hash.pdf personal.txt | sha224sum >> hash.txt
  cat hash.pdf personal_.txt | sha224sum >> hash.txt
  # sha256sum
  cat hash.pdf personal.txt | sha256sum >> hash.txt
  cat hash.pdf personal_.txt | sha256sum >> hash.txt
  # sha384sum
  cat hash.pdf personal.txt | sha384sum >> hash.txt
  cat hash.pdf personal_.txt | sha384sum >> hash.txt
  # sha512sum
  cat hash.pdf personal.txt | sha512sum >> hash.txt
  cat hash.pdf personal_.txt | sha512sum >> hash.txt
fi
