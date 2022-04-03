bash compile.sh

# fazer os sets de teste
# padrões pequenos
# time build/src/pmt -c "i" test_data/english_1024MB.txt
# time build/src/pmt -c "my" test_data/english_1024MB.txt
# time build/src/pmt -c "thy" test_data/english_1024MB.txt
# time build/src/pmt -c "love" test_data/english_1024MB.txt
time build/src/pmt -c "thick" test_data/english_1024MB.txt
time build/src/pmt -c "afraid" test_data/english_1024MB.txt
time build/src/pmt -c "memento" test_data/english_1024MB.txt
time build/src/pmt -c "fearless" test_data/english_1024MB.txt
time build/src/pmt -c "resources" test_data/english_1024MB.txt
time build/src/pmt -c "characters" test_data/english_1024MB.txt

# time build/src/pmt -c "i" test_data/english_1024MB.txt
# time build/src/pmt -c "my" test_data/english_1024MB.txt
# time build/src/pmt -c "thy" test_data/english_1024MB.txt
# time build/src/pmt -c "love" test_data/english_1024MB.txt
# time build/src/pmt -c "thick" test_data/english_1024MB.txt
time build/src/pmt -a kmp -c "afraid" test_data/english_1024MB.txt
time build/src/pmt -a kmp -c "memento" test_data/english_1024MB.txt
time build/src/pmt -a kmp -c "fearless" test_data/english_1024MB.txt
time build/src/pmt -a kmp -c "resources" test_data/english_1024MB.txt
time build/src/pmt -a kmp -c "characters" test_data/english_1024MB.txt

# time build/src/pmt -c "i" test_data/english_1024MB.txt
# time build/src/pmt -c "my" test_data/english_1024MB.txt
# time build/src/pmt -c "thy" test_data/english_1024MB.txt
# time build/src/pmt -c "love" test_data/english_1024MB.txt
# time build/src/pmt -c "thick" test_data/english_1024MB.txt
time build/src/pmt -a aho_corasick -c "afraid" test_data/english_1024MB.txt
time build/src/pmt -a aho_corasick -c "memento" test_data/english_1024MB.txt
time build/src/pmt -a aho_corasick -c "fearless" test_data/english_1024MB.txt
time build/src/pmt -a aho_corasick -c "resources" test_data/english_1024MB.txt
time build/src/pmt -a aho_corasick -c "characters" test_data/english_1024MB.txt

# time build/src/pmt -c "i" test_data/english_1024MB.txt
# time build/src/pmt -c "my" test_data/english_1024MB.txt
# time build/src/pmt -c "thy" test_data/english_1024MB.txt
# time build/src/pmt -c "love" test_data/english_1024MB.txt
# time build/src/pmt -c "thick" test_data/english_1024MB.txt
time build/src/pmt -a wu_manber -c "afraid" test_data/english_1024MB.txt
time build/src/pmt -a wu_manber -c "memento" test_data/english_1024MB.txt
time build/src/pmt -a wu_manber -c "fearless" test_data/english_1024MB.txt
time build/src/pmt -a wu_manber -c "resources" test_data/english_1024MB.txt
time build/src/pmt -a wu_manber -c "characters" test_data/english_1024MB.txt


# time build/src/pmt -c "characters" test_data/english_ascii.txt
# time build/src/pmt -c "love" test_data/english_ascii.txt
# time build/src/pmt -c "love" test_data/english_ascii.txt