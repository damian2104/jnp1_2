Oto kod który napisałam. Są wszystkie pliki o które proszą w zadaniu, tylko trzeba im jeszcze coś podopisywać.

Co jest:
- strdeque.cc wraz ze wszyskimi funkcjami z treści zadania.
- strdequeconst.cc które nic nie robi, bo trochę nie wiem co właściwie tu ma się zadziać.
- strdeque.h i strdequeconst.h w których moim zdaniem jest wszystko co powinno być, jednak możesz jeszcze na to spojrzeć.
- cstrdeque, cstrdequeconst, które robią to co sobie wyobrażam, że miałyby robić, chociaż nie jestem pewna czy o to chodzi. W każdym razie to współpracuje z przykładem z zadania.

Czego nie ma:
- tej części polecenia: Moduły strdeque i strdequeconst powinny sprawdzać poprawność parametrów i wykonania funkcji za pomocą asercji i wypisywać na standardowy strumień błędów informacje diagnostyczne. Kompilowanie z parametrem -DNDEBUG powinno wyłączać sprawdzanie i wypisywanie.
- strdequeconst.cc nic nie robi

Prosiłabym jeszcze, żebyś się przyjrzał plikowi strdeque.cc, czy na pewno wszystko jest ok. Może opowiem co się tam dzieje:
-Kolejki trzymam w mapie, podsłuchałam, że ktoś tak robi, są wspomniane w treści no i przede wszystkim chyba działają szybko.
-Zdefiniowałam sobie typy na my_deque i my_map, to chyba jest jasne.
-Oprócz funkcji ze specyfikacji zadania, jest funkcja find_deq, która zwraca referencje do kolejki jeśli istnieje, lub tworzy nową kolejkę jeżeli niczego nie wyszukano (nie wiem czy to ładne rozwiązanie, ale coś zwrócić trzeba...). Użycie referencji ma zapewnić po pierwsze, że zmienimy kolejkę która znajduje się w mapie a nie jej kopię. A po drugie, że nie marnujemy czasu na kopiowanie kolejki. Moja pierwsza koncepcja była taka, żeby robić kopię kolejki i ją edytować, starą usunąć z mapy i dodać nową, ale odrzuciłam to właśnie ze względu na koszt tworzenia kopii. Jednym z jej parametrów jest referencja do bool success, który ustawiam w zależności od tego czy wyszukiwanie się powiodło.
-Są funkcje my_map& strings() i unsigned long next_id() które służą ukrywaniu zmiennych globalnych. Nie wiem czy dobrze zrozumiałam, że tak to mamy robić, więc jeśli się mylę to popraw.

Możemy się umówić tak, że ja ogarnę jeszcze strdequeconst.cc a Ty te wszystkie aserty i kompilację z -DNDEBUG?