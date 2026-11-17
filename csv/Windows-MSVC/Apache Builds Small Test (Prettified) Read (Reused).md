
----
### Apache Builds Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1756.82 | 0.209013 | 213.595ms | 3370 | 160 | 2339.23 | 1829.38 | 0.0341763 | 1.71439 | 1(Win) | true |
| Jsonifier | 1537.74 | 0.286672 | 246.08ms | 3370 | 40 | 1435.9 | 2090 | 0 | 1.9621 | 2(Loss) | true |
| Glaze | 1491.1 | 0.100493 | 248.438ms | 3370 | 4890 | 22942 | 2155.38 | 0.296908 | 2.01917 | 3(Loss) | true |
| simdjson (ondemand) | 1297.88 | 0.145392 | 274.848ms | 3370 | 160 | 2073.9 | 2476.25 | 0.151668 | 2.33044 | 4(Loss) | true |
