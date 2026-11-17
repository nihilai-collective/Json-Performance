
----
### Apache Builds Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2288.39 | 0.065708 | 5946.98ms | 94653 | 4890 | 3.28513e+06 | 39446.1 | 0.0592466 | 2.21375 | 11.0843 | 1.98275 | 0.0057676 | 1.23128e-05 | 7.9334e-06 | 1(Win) | true |
| simdjson (ondemand) | 1630.32 | 0.0969358 | 7478.8ms | 94653 | 160 | 460905 | 55368.4 | 0.0321812 | 3.12686 | 12.1068 | 2.24341 | 0.00882704 | 9.70651e-06 | 5.87673e-06 | 2(Loss) | true |
