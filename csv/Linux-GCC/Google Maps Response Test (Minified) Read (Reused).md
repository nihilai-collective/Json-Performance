
----
### Google Maps Response Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2902.3 | 0.0794047 | 1176.24ms | 11812 | 1280 | 12158.1 | 3881.34 | 0.13373 | 1.78286 | 9.20166 | 1.40019 | 0.00134324 | 3.49883e-05 | 8.73053e-06 | 1(Win) | true |
| Glaze | 2184.13 | 0.0371917 | 1301.87ms | 11812 | 4890 | 17992.4 | 5157.56 | 0.023845 | 2.35539 | 12.0412 | 2.3786 | 0.000781552 | 2.89643e-05 | 5.88636e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 1985.18 | 0.0317973 | 1360.81ms | 11812 | 4890 | 15919.7 | 5674.44 | 0.0817279 | 2.56429 | 12.65 | 1.9321 | 0.00597886 | 3.12669e-05 | 1.09244e-05 | 3(Loss) | true |
| simdjson (reflection) | 1605.3 | 0.0371376 | 1497.86ms | 11812 | 4890 | 33210.2 | 7017.25 | 0.0949041 | 3.16752 | 12.9909 | 2.03844 | 0.00318549 | 3.06264e-05 | 1.16862e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1181.74 | 0.0588419 | 1749.5ms | 11812 | 1280 | 40270.7 | 9532.42 | 0.0761621 | 4.32177 | 17.0123 | 3.02938 | 0.00760575 | 2.83742e-05 | 1.09132e-05 | 5(Loss) | true |
