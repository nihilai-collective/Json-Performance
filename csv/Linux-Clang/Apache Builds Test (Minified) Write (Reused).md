
----
### Apache Builds Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16776.1 | 0.0453065 | 1277.57ms | 94653 | 2560 | 15214.1 | 5380.75 | 0.00167696 | 0.303509 | 1.32453 | 0.182678 | 0.000142399 | 4.81198e-06 | 2.1006e-06 | 1(Win) | true |
| Glaze | 6318.86 | 0.0689355 | 2177.05ms | 94653 | 1280 | 124133 | 14285.5 | 0.0156159 | 0.797669 | 4.32645 | 0.655341 | 5.71826e-05 | 6.28942e-06 | 3.49962e-06 | 2(Loss) | true |
