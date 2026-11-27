
----
### Google Maps Response Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2819.35 | 0.175392 | 1162.52ms | 11812 | 640 | 31430.5 | 3995.54 | 0.0307077 | 1.81766 | 8.94269 | 1.58136 | 0.00171105 | 4.06102e-05 | 1.91807e-05 | 1(Win) | true |
| simdjson (ondemand) | 2142.95 | 0.0952825 | 1279.65ms | 11812 | 1280 | 32111.3 | 5256.68 | 0.171147 | 2.39781 | 10.8839 | 1.82061 | 0.00273378 | 4.17346e-05 | 1.52784e-05 | 2(Loss) | true |
