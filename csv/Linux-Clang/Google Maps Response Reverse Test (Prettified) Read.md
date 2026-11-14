
----
### Google Maps Response Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1537.46 | 0.0950598 | 2306.94ms | 25388 | 320 | 71712.4 | 15748 | 0.0964146 | 3.35704 | 14.9887 | 2.93773 | 0.00730894 | 7.75465e-06 | 1.60017e-06 | 1(Win) | true |
| simdjson (ondemand) | 1442.09 | 0.050267 | 2397.59ms | 25388 | 1280 | 91168.9 | 16789.4 | 0.120773 | 3.56422 | 16.0589 | 2.87307 | 0.00695918 | 1.13858e-05 | 1.90789e-06 | 2(Loss) | true |
