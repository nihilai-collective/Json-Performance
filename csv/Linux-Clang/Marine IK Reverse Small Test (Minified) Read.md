
----
### Marine IK Reverse Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 821.126 | 0.0867443 | 559.497ms | 4604 | 80 | 1721.17 | 5347.19 | 0.0577073 | 2.99904 | 1(Win) | true |
| Jsonifier (two-stage) | 718.46 | 0.718511 | 603.02ms | 4604 | 640 | 1.23399e+06 | 6111.29 | 1.23111 | 3.42859 | 2(Loss) | true |
| Glaze | 567.533 | 0.0797907 | 764.15ms | 4604 | 80 | 3048.48 | 7736.5 | 0.274779 | 4.34578 | 3(Loss) | true |
| simdjson (ondemand) | 521.442 | 0.116984 | 863.441ms | 4604 | 30 | 2910.92 | 8420.33 | 0.00395851 | 4.73277 | 4(Loss) | true |
