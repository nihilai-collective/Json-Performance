
----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1269.61 | 0.153444 | 9072.68ms | 461466 | 40 | 1.1316e+07 | 346632 | 0.0154126 | 3.97833 | 17.369 | 3.29552 | 0.0190257 | 0.0412135 | 7.21072e-05 | 1(Win) | true |
| Glaze | 1184.72 | 0.0709715 | 9694.95ms | 461466 | 640 | 4.44833e+07 | 371471 | 0.0698511 | 4.24863 | 19.1627 | 3.79018 | 0.0132607 | 0.031469 | 0.000103366 | 2(Loss) | true |
| Jsonifier (two-stage) | 1100.14 | 0.0512307 | 5191.24ms | 461466 | 640 | 2.68797e+07 | 400030 | 0.0375617 | 4.58515 | 18.8407 | 3.5557 | 0.0244441 | 0.0857891 | 0.000150126 | 3(Loss) | true |
| simdjson (ondemand) | 828.403 | 0.169192 | 6896.42ms | 461466 | 160 | 1.29263e+08 | 531249 | 0.158692 | 6.06037 | 25.2962 | 4.4775 | 0.0105948 | 0.0854267 | 0.000184764 | 4(Loss) | true |
