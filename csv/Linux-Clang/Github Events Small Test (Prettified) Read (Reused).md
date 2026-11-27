
----
### Github Events Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3557.37 | 0.182237 | 68.635ms | 2158 | 40 | 44.4609 | 578.525 | 0.196952 | 0.66469 | 1(Win) | true |
| Jsonifier (two-stage) | 3118.23 | 0.19695 | 75.9948ms | 2158 | 30 | 50.6897 | 660 | 0.0504796 | 0.763809 | 2(Loss) | true |
| Glaze | 2440.74 | 0.185933 | 92.5094ms | 2158 | 40 | 98.3179 | 843.2 | 0.0868947 | 0.982762 | 3(Loss) | true |
| simdjson (ondemand) | 2125.21 | 0.287101 | 105.609ms | 2158 | 4890 | 37798.8 | 968.39 | 0.0891165 | 1.13177 | 4(Loss) | true |
