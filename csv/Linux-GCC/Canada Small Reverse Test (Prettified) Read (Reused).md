
----
### Canada Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1975.25 | 0.0616756 | 1380.45ms | 11579 | 1280 | 15217.1 | 5590.47 | 0.132754 | 2.62591 | 13.2742 | 2.30098 | 0.000961331 | 1.41015e-05 | 4.52058e-06 | 1(Win) | true |
| Jsonifier (generic) | 1743.58 | 0.0747413 | 1450.26ms | 11579 | 1280 | 28680.5 | 6333.27 | 0.0258612 | 2.9771 | 12.9794 | 2.46196 | 0.0034212 | 2.4762e-05 | 8.50138e-06 | 2(Loss) | true |
