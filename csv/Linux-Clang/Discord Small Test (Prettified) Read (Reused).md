
----
### Discord Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3421.63 | 0.0513219 | 208.551ms | 6701 | 80 | 73.5038 | 1867.7 | 0.12433 | 0.713513 | 1(Win) | true |
| Jsonifier (two-stage) | 2973.31 | 0.0556055 | 241.093ms | 6701 | 80 | 114.268 | 2149.31 | 0.100512 | 0.822351 | 2(Loss) | true |
| Glaze | 2407.68 | 0.0576444 | 284.185ms | 6701 | 80 | 187.278 | 2654.25 | 0.188733 | 1.01805 | 3(Loss) | true |
| simdjson (ondemand) | 1209.08 | 0.0759907 | 548.811ms | 6701 | 40 | 645.281 | 5285.48 | 0.0477496 | 2.03729 | 4(Loss) | true |
