
----
### Twitter Partial Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 6844.28 | 0.0683826 | 43.2676ms | 2889 | 320 | 24.2483 | 402.55 | 0.0775699 | 0.338319 | 1(Win) | true |
| Jsonifier | 6623.12 | 0.0548718 | 44.8027ms | 2889 | 1280 | 66.6927 | 415.992 | 0.0533079 | 0.350414 | 2(Loss) | true |
| Jsonifier (two-stage) | 6484.74 | 0.11529 | 44.9929ms | 2889 | 320 | 76.779 | 424.869 | 0.139554 | 0.358735 | 3(Loss) | true |
| Glaze | 3487.83 | 0.039896 | 82.5995ms | 2889 | 320 | 31.7829 | 789.938 | 0.28481 | 0.686703 | 4(Loss) | true |
