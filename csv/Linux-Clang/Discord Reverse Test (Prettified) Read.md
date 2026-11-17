
----
### Discord Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 901.879 | 0.0647609 | 9642.95ms | 83958 | 640 | 2.1156e+06 | 88779.8 | 0.0638908 | 5.68366 | 25.0917 | 5.23911 | 0.00795234 | 2.14951e-05 | 9.06331e-06 | 1(Win) | true |
| simdjson (ondemand) | 297.28 | 0.0815909 | 7078.44ms | 83958 | 320 | 1.54535e+07 | 269337 | 0.0205868 | 17.2133 | 93.9956 | 18.8319 | 0.0235326 | 1.567e-05 | 5.65759e-06 | 2(Loss) | true |
