
----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2806.44 | 0.389287 | 362.264ms | 9378 | 1280 | 196997 | 3186.8 | 0.40005 | 1(Win) | true |
| Jsonifier (two-stage) | 2595.04 | 0.827726 | 421.067ms | 9378 | 320 | 260408 | 3446.4 | 0.185357 | 2(Loss) | true |
| simdjson (reflection) | 2007.44 | 0.25707 | 518.835ms | 9378 | 2560 | 335798 | 4455.2 | 0.496256 | 3(Loss) | true |
| Glaze | 1802.01 | 0.160658 | 549.435ms | 9378 | 2560 | 162761 | 4963.1 | 0.309228 | 4(Loss) | true |
| simdjson (ondemand) | 1539.55 | 0.196048 | 631.792ms | 9378 | 2560 | 332045 | 5809.2 | 0.0482227 | 5(Loss) | true |
