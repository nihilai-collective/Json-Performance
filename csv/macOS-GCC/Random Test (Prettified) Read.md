
----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1135.96 | 0.502321 | 7566.23ms | 728486 | 160 | 1.51007e+09 | 611586 | 2.70993 | 1(Win) | true |
| simdjson (reflection) | 1023.08 | 0.66679 | 8876.58ms | 728486 | 80 | 1.64018e+09 | 679066 | 1.29647 | 2(Loss) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 926.413 | 0.543421 | 8944.89ms | 728486 | 80 | 1.32861e+09 | 749923 | 1.1861 | 3(Tie) | true |
| Glaze STATISTICAL TIE | 921.241 | 1.24913 | 9158.32ms | 728486 | 30 | 2.66215e+09 | 754133 | 4.98836 | 3(Tie) | true |
| simdjson (ondemand) | 844.629 | 1.18858 | 10035.6ms | 728486 | 30 | 2.8674e+09 | 822537 | 0.512963 | 5(Loss) | true |
