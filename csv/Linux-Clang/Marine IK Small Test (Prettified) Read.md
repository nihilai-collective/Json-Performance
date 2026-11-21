
----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3056.58 | 0.104652 | 617.284ms | 18245 | 4890 | 173547 | 5692.57 | 0.168081 | 0.806025 | 1(Win) | true |
| Jsonifier | 2438.4 | 0.0835396 | 721.9ms | 18245 | 30 | 1066.06 | 7135.73 | 0.00887631 | 1.0114 | 2(Loss) | true |
| simdjson (ondemand) | 2005.59 | 0.0443006 | 895.851ms | 18245 | 80 | 1181.72 | 8675.66 | 0.14848 | 1.23103 | 3(Loss) | true |
| Glaze | 1892.89 | 0.153613 | 927.523ms | 18245 | 1280 | 255212 | 9192.16 | 0.366315 | 1.30416 | 4(Loss) | true |
