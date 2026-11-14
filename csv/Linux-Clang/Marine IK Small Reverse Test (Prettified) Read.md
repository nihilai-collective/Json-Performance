
----
### Marine IK Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1221.22 | 0.0224021 | 2152.78ms | 18245 | 2560 | 26080.6 | 14247.8 | 0.0397326 | 4.22844 | 18.5961 | 3.76876 | 0.00507633 | 2.51353e-05 | 9.29193e-06 | 1(Win) | true |
| simdjson (ondemand) | 860.06 | 0.0220669 | 2745.69ms | 18245 | 2560 | 51021.7 | 20230.9 | 0.00777872 | 5.99751 | 28.4352 | 5.55837 | 0.00625283 | 2.84753e-05 | 7.36503e-06 | 2(Loss) | true |
