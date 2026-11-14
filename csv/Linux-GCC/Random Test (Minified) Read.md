
----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1354.91 | 0.230726 | 7598.13ms | 409725 | 40 | 1.77099e+07 | 288391 | 0.161369 | 3.75304 | 18.0203 | 3.50719 | 0.00902136 | 0.0228997 | 2.45286e-05 | 1(Win) | true |
| simdjson (ondemand) | 983.729 | 0.167849 | 5153.93ms | 409725 | 40 | 1.778e+07 | 397207 | 0.316677 | 5.15882 | 19.9526 | 3.79085 | 0.0166393 | 0.0350317 | 1.70236e-05 | 2(Loss) | true |
