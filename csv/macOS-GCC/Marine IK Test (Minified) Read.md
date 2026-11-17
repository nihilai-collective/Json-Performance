
----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 611.979 | 0.731641 | 9013.29ms | 1834197 | 80 | 3.4987e+10 | 2.85831e+06 | 1.39638 | 1(Win) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 482.786 | 1.07355 | 5461.08ms | 1834197 | 40 | 6.05179e+10 | 3.62319e+06 | 0.795505 | 2(Tie) | true |
| Glaze STATISTICAL TIE | 477.332 | 0.848532 | 6025.06ms | 1834197 | 30 | 2.90074e+10 | 3.66459e+06 | 0.391566 | 2(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 419.001 | 1.45277 | 6421.56ms | 1834197 | 40 | 1.47134e+11 | 4.17475e+06 | 0.806609 | 4(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 418.008 | 0.548739 | 6312.19ms | 1834197 | 80 | 4.21837e+10 | 4.18467e+06 | 0.15348 | 4(Tie) | true |
