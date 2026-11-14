
----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2686.7 | 0.155269 | 964.187ms | 5839 | 2560 | 26512.3 | 2072.62 | 0.107071 | 1.92007 | 7.9262 | 1.24645 | 0.00078881 | 2.42175e-05 | 1.73938e-06 | 1(Win) | true |
| Jsonifier | 2030.87 | 0.179287 | 1030.05ms | 5839 | 4890 | 118173 | 2741.93 | 0.147196 | 2.52544 | 8.96695 | 1.85631 | 0.00140722 | 3.49879e-05 | 8.26542e-06 | 2(Loss) | true |
| Glaze | 2002.96 | 0.105722 | 1036.38ms | 5839 | 4890 | 42244.8 | 2780.13 | 0.119729 | 2.56138 | 10.3523 | 1.94622 | 0.00149565 | 3.70193e-05 | 6.75943e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1926.06 | 0.0930671 | 1049.15ms | 5839 | 4890 | 35403 | 2891.14 | 0.166775 | 2.66041 | 10.3017 | 1.53639 | 0.000996018 | 3.00147e-05 | 2.76681e-06 | 4(Loss) | true |
