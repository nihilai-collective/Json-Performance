
----
### Discord Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1013.99 | 0.0234873 | 9002.43ms | 83958 | 2560 | 880564 | 78963.8 | 0.0681133 | 5.01051 | 22.6829 | 4.73781 | 0.0064565 | 3.46807e-05 | 2.38354e-05 | 1(Win) | true |
| simdjson (ondemand) | 294.128 | 0.0694106 | 7254.92ms | 83958 | 320 | 1.14249e+07 | 272223 | 0.0171154 | 17.1819 | 87.954 | 18.6212 | 0.021166 | 9.82262e-05 | 8.02485e-05 | 2(Loss) | true |
