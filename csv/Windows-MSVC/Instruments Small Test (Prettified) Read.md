
----
### Instruments Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1861.66 | 0.220227 | 430.543ms | 7932 | 30 | 2402.3 | 4063.33 | 0.1638 | 1.32152 | 1(Win) | true |
| Jsonifier (two-stage) | 1693.71 | 0.119117 | 466.468ms | 7932 | 80 | 2264.24 | 4466.25 | 0.139743 | 1.45271 | 2(Loss) | true |
| Glaze | 1283.21 | 0.0597862 | 609.626ms | 7932 | 160 | 1987.42 | 5895 | 0.233794 | 1.9197 | 3(Loss) | true |
| simdjson (ondemand) | 1246.27 | 0.222983 | 619.792ms | 7932 | 4890 | 895762 | 6069.73 | 0.0464831 | 1.97716 | 4(Loss) | true |
