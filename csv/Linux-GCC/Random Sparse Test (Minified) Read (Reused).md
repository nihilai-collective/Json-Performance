
----
### Random Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2817.84 | 0.0232488 | 8432.73ms | 409725 | 2560 | 2.66069e+06 | 138668 | 0.242742 | 1.80756 | 9.16679 | 1.55604 | 0.00405757 | 0.000481684 | 3.53515e-06 | 1(Win) | true |
| simdjson (ondemand) | 2160.38 | 0.0746118 | 5237.24ms | 409725 | 160 | 2.91381e+06 | 180869 | 0.0181691 | 2.35048 | 9.82371 | 1.60777 | 0.00547266 | 0.00108167 | 2.13558e-06 | 2(Loss) | true |
