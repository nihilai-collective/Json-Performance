
----
### Discord Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1003.63 | 0.0235334 | 9074.03ms | 83958 | 2560 | 902373 | 79778.9 | 0.146367 | 5.06287 | 23.626 | 4.82547 | 0.00651198 | 3.84353e-05 | 3.06422e-05 | 1(Win) | true |
| simdjson (ondemand) | 302.306 | 0.06216 | 7072.1ms | 83958 | 640 | 1.73473e+07 | 264859 | 0.201175 | 16.7769 | 92.4129 | 18.4906 | 0.0245918 | 8.78788e-05 | 7.17062e-05 | 2(Loss) | true |
