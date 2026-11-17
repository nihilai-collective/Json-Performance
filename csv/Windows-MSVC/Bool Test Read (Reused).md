
----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 752.494 | 0.104402 | 117.652ms | 905 | 4890 | 7011.58 | 1146.95 | 0.184236 | 3.97627 | 1(Win) | true |
| Glaze | 732.05 | 0.190574 | 120.84ms | 905 | 1280 | 6461.83 | 1178.98 | 0.218196 | 4.08026 | 2(Loss) | true |
| Jsonifier (two-stage) | 277.628 | 0.121098 | 311.534ms | 905 | 1280 | 18140.7 | 3108.75 | 0.225666 | 10.8616 | 3(Loss) | true |
| simdjson (ondemand) | 126.908 | 0.0622202 | 680.778ms | 905 | 4890 | 87557.1 | 6800.8 | 0.188417 | 23.8873 | 4(Loss) | true |
