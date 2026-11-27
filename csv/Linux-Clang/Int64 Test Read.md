
----
### Int64 Test Read Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 1911.84 | 0.17378 | 773.853ms | 1313 | 160 | 207.275 | 654.956 | 0.0696126 | 2.85668 | 10.7738 | 2.64737 | 0.000813976 | 0.000128522 | 5.2361e-05 | 1(Win) | true |
| simdjson (stage-1) | 1162.78 | 0.161344 | 812.597ms | 1313 | 320 | 966.034 | 1076.88 | 0.0159629 | 4.59812 | 23.1013 | 5.15918 | 0.00137329 | 8.33016e-05 | 1.19002e-05 | 2(Loss) | true |
