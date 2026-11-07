
----
### Google Maps Response Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2514.87 | 0.123279 | 1082.16ms | 25388 | 40 | 5634.62 | 9627.5 | 0.439504 | 0.981426 | 1(Win) | true |
| Jsonifier | 2412.11 | 0.407528 | 1165.22ms | 25388 | 640 | 1.07093e+06 | 10037.7 | 0.447854 | 1.02346 | 2(Loss) | true |
| Glaze | 1616.01 | 0.406327 | 1587.06ms | 25388 | 320 | 1.18596e+06 | 14982.5 | 0.51153 | 1.52855 | 3(Loss) | true |
| simdjson (ondemand) | 1194.6 | 0.203104 | 2178.74ms | 25388 | 1280 | 2.169e+06 | 20267.8 | 0.0808818 | 2.06952 | 4(Loss) | true |
