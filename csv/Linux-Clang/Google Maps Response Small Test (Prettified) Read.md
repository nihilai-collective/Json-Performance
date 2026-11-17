
----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3188.97 | 0.101621 | 1023.12ms | 9378 | 2560 | 20793.4 | 2804.53 | 0.048564 | 1.60339 | 7.46129 | 1.20633 | 0.00149173 | 2.12432e-05 | 3.33227e-06 | 1(Win) | true |
| Jsonifier | 2600.9 | 0.112781 | 1085.93ms | 9378 | 2560 | 38502.5 | 3438.64 | 0.0481663 | 1.96719 | 8.21753 | 1.7283 | 0.00303965 | 4.31529e-05 | 1.5495e-05 | 2(Loss) | true |
| Glaze | 2398.2 | 0.0991249 | 1113.84ms | 9378 | 2560 | 34982.9 | 3729.28 | 0.321815 | 2.11902 | 9.73363 | 1.90499 | 0.00274258 | 4.61102e-05 | 1.72028e-05 | 3(Loss) | true |
| simdjson (ondemand) | 2156.93 | 0.0676298 | 1154.73ms | 9378 | 4890 | 38453.4 | 4146.43 | 0.240471 | 2.37146 | 10.2052 | 1.62039 | 0.00139935 | 5.20515e-05 | 1.99091e-05 | 4(Loss) | true |
