
----
### Discord Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11294.8 | 0.345817 | 771.639ms | 4857 | 40 | 80.4513 | 410.1 | 0.469218 | 0.493406 | 1.54766 | 0.245831 | 0.000211036 | 5.14721e-06 | 0 | 1(Win) | true |
| simdjson (reflection) | 8483.53 | 0.25963 | 778.946ms | 4857 | 4890 | 9826.54 | 545.998 | 0.033556 | 0.649983 | 1.94173 | 0.303891 | 0.000206309 | 5.57036e-05 | 3.34306e-05 | 2(Loss) | true |
| Glaze | 4754.59 | 0.424078 | 822.294ms | 4857 | 320 | 5461.99 | 974.216 | 0.00994489 | 1.12528 | 3.23286 | 0.496603 | 0.000208462 | 3.41003e-05 | 5.14721e-06 | 3(Loss) | true |
