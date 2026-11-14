
----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1227.4 | 0.124707 | 344.026ms | 4390 | 4890 | 88480.3 | 3410.98 | 0.593425 | 2.462 | 1(Win) | true |
| Jsonifier (two-stage) | 1071.21 | 0.214049 | 394.69ms | 4390 | 4890 | 342228 | 3908.32 | 0.0840976 | 2.82325 | 2(Loss) | true |
| Glaze | 943.466 | 0.251142 | 448.782ms | 4390 | 40 | 4967.95 | 4437.5 | 0.0187829 | 3.2014 | 3(Loss) | true |
| simdjson (ondemand) | 589.718 | 0.127257 | 716.064ms | 4390 | 640 | 52237.5 | 7099.38 | 0.140659 | 5.14009 | 4(Loss) | true |
