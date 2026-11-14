
----
### Random Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2383.25 | 0.294797 | 9375.59ms | 728486 | 640 | 4.72638e+08 | 291508 | 0.521815 | 2.11513 | 9.92385 | 1.57253 | 0.00724395 | 0.013803 | 0.000126407 | 1(Win) | true |
| simdjson (reflection) | 2350.72 | 0.440241 | 9467.48ms | 728486 | 40 | 6.77147e+07 | 295543 | 0.0255019 | 2.14222 | 10.022 | 1.54434 | 0.00232698 | 0.0232365 | 0.000294584 | 2(Loss) | true |
| Jsonifier | 2026.92 | 0.188507 | 5280.63ms | 728486 | 640 | 2.67182e+08 | 342757 | 0.096129 | 2.50926 | 10.6014 | 1.96469 | 0.00807091 | 0.00395668 | 0.000108502 | 3(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 1911.77 | 1.20714 | 5450.47ms | 728486 | 320 | 6.15796e+09 | 363401 | 0.666049 | 2.64673 | 10.8529 | 1.72342 | 0.00208123 | 0.0274706 | 0.000189481 | 4(Tie) | true |
| Glaze STATISTICAL TIE | 1907.58 | 0.19413 | 5532.38ms | 728486 | 320 | 1.59961e+08 | 364199 | 0.185897 | 2.65995 | 12.599 | 2.38206 | 0.00868915 | 0.00392014 | 0.000120052 | 4(Tie) | true |
