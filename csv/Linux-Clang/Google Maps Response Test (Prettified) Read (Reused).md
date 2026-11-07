
----
### Google Maps Response Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3828.15 | 0.0589402 | 671.239ms | 25388 | 40 | 555.856 | 6324.7 | 0.0231841 | 0.644156 | 1(Win) | true |
| Jsonifier | 3360.86 | 0.0261793 | 762.183ms | 25388 | 40 | 142.276 | 7204.07 | 0.00381743 | 0.734047 | 2(Loss) | true |
| Glaze | 2645.4 | 0.053441 | 958.08ms | 25388 | 30 | 717.702 | 9152.43 | 0.0440879 | 0.933195 | 3(Loss) | true |
| simdjson (ondemand) | 2075.52 | 0.0837378 | 1208.64ms | 25388 | 4890 | 466610 | 11665.4 | 0.0178979 | 1.1899 | 4(Loss) | true |
