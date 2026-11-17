
----
### Google Maps Response Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11379.8 | 0.206181 | 767.774ms | 4390 | 40 | 23.0154 | 367.9 | 0.190632 | 0.494499 | 2.14055 | 0.346014 | 0.00022779 | 1.13895e-05 | 0 | 1(Win) | true |
| Glaze | 4037.45 | 0.142993 | 835.853ms | 4390 | 4890 | 10751.1 | 1036.95 | 0.313728 | 1.30285 | 5.37927 | 0.771071 | 0.000530905 | 5.03095e-05 | 1.43941e-05 | 2(Loss) | true |
