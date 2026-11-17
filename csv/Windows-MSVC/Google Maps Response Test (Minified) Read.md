
----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 677.768 | 0.13039 | 1702.35ms | 11812 | 4890 | 2.2966e+06 | 16620.4 | 0.0935664 | 3.64609 | 1(Win) | true |
| simdjson (ondemand) | 566.152 | 0.26746 | 2008.22ms | 11812 | 2560 | 7.25001e+06 | 19897.1 | 0.208256 | 4.36663 | 2(Loss) | true |
