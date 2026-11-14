
----
### Canada Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1840.7 | 0.168742 | 9581.08ms | 5212421 | 160 | 3.32261e+09 | 2.70058e+06 | 1.16022 | 2.76929 | 12.589 | 2.16751 | 0.0100508 | 0.109983 | 0.0008904 | 1(Win) | true |
| Jsonifier (generic) | 1778.22 | 0.480815 | 9838.22ms | 5212421 | 160 | 2.89057e+10 | 2.79546e+06 | 0.141158 | 2.86416 | 12.3782 | 2.35386 | 0.00980679 | 0.0901382 | 0.000742502 | 2(Loss) | true |
