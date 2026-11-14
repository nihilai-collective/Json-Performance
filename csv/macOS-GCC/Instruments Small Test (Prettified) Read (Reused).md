
----
### Instruments Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2959.38 | 0.299142 | 270.214ms | 7932 | 4890 | 285909 | 2556.13 | 0.52802 | 1(Win) | true |
| Jsonifier (two-stage) | 2582.46 | 0.226997 | 330.39ms | 7932 | 2560 | 113182 | 2929.2 | 0.55001 | 2(Loss) | true |
| Glaze | 2125.29 | 0.313362 | 380.192ms | 7932 | 2560 | 318465 | 3559.3 | 0.109692 | 3(Loss) | true |
| simdjson (reflection) | 2031.33 | 0.205626 | 389.033ms | 7932 | 4890 | 286727 | 3723.94 | 0.410874 | 4(Loss) | true |
| simdjson (ondemand) | 1835.81 | 0.156014 | 418.862ms | 7932 | 4890 | 202091 | 4120.55 | 0.0835847 | 5(Loss) | true |
