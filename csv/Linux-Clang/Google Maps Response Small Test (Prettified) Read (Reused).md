
----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 4019.71 | 0.050286 | 244.218ms | 9378 | 160 | 200.284 | 2224.93 | 0.0297674 | 0.608833 | 1(Win) | true |
| Jsonifier | 3443.59 | 0.0354816 | 282.541ms | 9378 | 80 | 67.9353 | 2597.16 | 0.193586 | 0.711808 | 2(Loss) | true |
| Glaze | 2751.64 | 0.0325031 | 342.535ms | 9378 | 80 | 89.2847 | 3250.26 | 0.0572702 | 0.892746 | 3(Loss) | true |
| simdjson (ondemand) | 2158.24 | 0.134347 | 431.498ms | 9378 | 4890 | 151559 | 4143.91 | 0.105713 | 1.13967 | 4(Loss) | true |
