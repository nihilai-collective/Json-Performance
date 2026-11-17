
----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2285.91 | 0.127622 | 493.648ms | 11812 | 40 | 1582.12 | 4927.93 | 0.428526 | 1.07696 | 1(Win) | true |
| Jsonifier (two-stage) | 1751.51 | 0.0929529 | 650.968ms | 11812 | 80 | 2859.14 | 6431.46 | 0.13604 | 1.40736 | 2(Loss) | true |
| Glaze | 1647.29 | 0.146903 | 690.343ms | 11812 | 2560 | 258348 | 6838.37 | 0.501324 | 1.49701 | 3(Loss) | true |
| simdjson (ondemand) | 899.492 | 0.402929 | 1253.05ms | 11812 | 320 | 814816 | 12523.5 | 0.162709 | 2.74611 | 4(Loss) | true |
