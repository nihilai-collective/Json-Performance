
----
### Instruments Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1671.4 | 0.100841 | 288.277ms | 4669 | 320 | 2309.46 | 2664.06 | 0.408879 | 1.46641 | 1(Win) | true |
| Jsonifier (two-stage) | 1172.54 | 0.0736496 | 405.728ms | 4669 | 160 | 1251.57 | 3797.5 | 0.230947 | 2.09535 | 2(Loss) | true |
| Glaze | 1028.93 | 0.123151 | 464.65ms | 4669 | 80 | 2272.15 | 4327.5 | 0.0578035 | 2.38997 | 3(Loss) | true |
| simdjson (ondemand) | 789.02 | 0.183864 | 615.255ms | 4669 | 30 | 3229.89 | 5643.33 | 0.23571 | 3.12175 | 4(Loss) | true |
