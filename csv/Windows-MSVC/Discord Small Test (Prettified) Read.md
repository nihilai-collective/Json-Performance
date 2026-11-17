
----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1170.43 | 0.141921 | 552.382ms | 6701 | 640 | 38428.8 | 5460 | 0.00572377 | 2.58643 | 1(Win) | true |
| Jsonifier | 1109.43 | 0.150347 | 583.826ms | 6701 | 1280 | 96001.5 | 5760.23 | 0.229738 | 2.72734 | 2(Loss) | true |
| Glaze | 1023.85 | 0.201727 | 633.566ms | 6701 | 640 | 101465 | 6241.72 | 0.0825413 | 2.95696 | 3(Loss) | true |
| simdjson (ondemand) | 894.203 | 0.298025 | 726.803ms | 6701 | 30 | 13609.2 | 7146.67 | 0.0466636 | 3.39894 | 4(Loss) | true |
