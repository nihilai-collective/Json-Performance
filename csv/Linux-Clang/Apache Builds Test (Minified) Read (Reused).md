
----
### Apache Builds Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2795.4 | 0.0488602 | 5244.32ms | 94653 | 2560 | 637281 | 32291.7 | 0.0187066 | 1.80585 | 9.4442 | 1.60825 | 0.00537997 | 1.83648e-05 | 1.21455e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 2295.58 | 0.0285108 | 5939.55ms | 94653 | 4890 | 614627 | 39322.6 | 0.122692 | 2.18489 | 11.0724 | 1.94418 | 0.00601021 | 1.14702e-05 | 6.44265e-06 | 2(Loss) | true |
| Glaze | 2066.94 | 0.0614326 | 6359.03ms | 94653 | 640 | 460672 | 43672.4 | 0.0411883 | 2.44638 | 11.9412 | 2.23915 | 0.00925165 | 3.48312e-06 | 5.94276e-07 | 3(Loss) | true |
| simdjson (ondemand) | 1683.26 | 0.0390513 | 7403.72ms | 94653 | 2560 | 1.12274e+06 | 53627 | 0.0536173 | 2.99969 | 12.9087 | 2.25941 | 0.00712914 | 1.2715e-05 | 5.71165e-06 | 4(Loss) | true |
