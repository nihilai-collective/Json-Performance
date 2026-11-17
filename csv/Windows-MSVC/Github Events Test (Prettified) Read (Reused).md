
----
### Github Events Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1444.21 | 0.0506545 | 5003.28ms | 65103 | 1280 | 606999 | 42990.4 | 0.0154492 | 2.10276 | 1(Win) | true |
| Glaze | 1408.64 | 0.0865209 | 5073.6ms | 65103 | 640 | 930727 | 44075.8 | 0.0527931 | 2.15644 | 2(Loss) | true |
| Jsonifier | 1372.59 | 0.0656654 | 5239.5ms | 65103 | 1280 | 1.12928e+06 | 45233.4 | 0.104728 | 2.21298 | 3(Loss) | true |
| simdjson (ondemand) | 1027.94 | 0.114406 | 6624.32ms | 65103 | 320 | 1.52796e+06 | 60399.4 | 0.0227703 | 2.9556 | 4(Loss) | true |
