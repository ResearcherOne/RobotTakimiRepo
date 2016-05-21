1-)Negatif Resimler

	Priz olmayan resimler. Positif resimlerin en az 2 kati olsun. Benim cogunu 
https://code.google.com/p/tutorial-haartraining/
reposundan aldim.
Resimler toplaninca bir klasorde, hepsini tek .txt / .dat falan bir dosyada log alman lazim.

	find ./negative_images -iname "*.jpg" > negatives.txt

2-)Pozitif Resimler

	Icerisinde priz olan resimler. Original resim ne kadar cok cekersen o kadar iyi.
Sonra create samples kullanarak OpenCV'nin istedigimiz kadar cogaltabiliriz bu resimleri kullanarak.
Cektiginiz resimleri sadece priz olacak sekilde crop yapmalisiniz.

	opencv_createsamples -img cropped00.jpg \
	-bg negatives.txt \
	-info positive_images/cropped00.txt \
	-num 128 -maxxangle 0.0 -maxyangle 0.0 -maxzangle 0.3 \
	-bgcolor 255 -bgthresh 8 -w 48 -h 48

-num olusturulacak resim sayisini gostermektedir.
-info ise olusan resimlerin logunu ve prizin nerede oldugunu gosteren koordinatlari icerir.
-w -h crop yaptiginiz prizlerin buyuklugudur.
-img kullandiginiz original resmin ismidir. Her resim icin ayri yapin bu kodu.

	cat cropped*.txt > positives.txt

3-) .vec Olusumu

Bu kod ile olusan tum -info .txt'lerini birlestiririz.

opencv_createsamples -info positive_images/positives.txt \
-bg negatives.txt \
-vec cropped.vec \
-num **** -w 48 -h 48

Bununla ise positive imagesleri kullanarak training yapmak icin .vec dosyasini olusturmak icin kullaniriz.
-num positives.txt'te belirtmis oldugun kac tane .jpg varsa onun sayisidir.

4-)Train Cascade

opencv_traincascade -data ./cascade -vec cropped.vec \
-bg negatives.txt \
-numPos **** -numNeg **** -numStages 10 \
-precalcValBufSize 1024 -precalcIdxBufSize 1024 \
-featureType HAAR \
-minHitRate 0.995 -maxFalseAlarmRate 0.5 \
-w 48 -h 48

-data Output klasoru
-vec olusturdugumuz .vec dosyasi
-numPos .vec olustururken girdigimiz -num sayisinin 0.9 kati
-numNeg negatives.txt'teki girilen resimlerin 0.9 kati

Birkac saat surebilir, sonunda cascade.xml diye dosya olacak /cascade klasorunde.
Bu .xml kullanacagimiz dosyadir tanimlamak icin prizleri.