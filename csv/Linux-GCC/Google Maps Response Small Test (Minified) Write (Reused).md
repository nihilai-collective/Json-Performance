
----
### Google Maps Response Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14231.1 | 0.0894848 | 757.991ms | 4390 | 640 | 44.3539 | 294.189 | 0.279618 | 0.409775 | 1.66743 | 0.260137 | 0.00022779 | 3.91515e-05 | 1.21014e-05 | 1(Win) | true |
| simdjson (reflection) | 8638.46 | 0.126252 | 777.374ms | 4390 | 80 | 29.9519 | 484.65 | 0.149817 | 0.634114 | 2.40979 | 0.364692 | 0.00022779 | 1.13895e-05 | 2.84738e-06 | 2(Loss) | true |
| Glaze | 4110.9 | 0.177307 | 838.454ms | 4390 | 1280 | 4173.66 | 1018.42 | 0.0835322 | 1.2787 | 4.36743 | 0.663098 | 0.000227968 | 2.11774e-05 | 6.76253e-06 | 3(Loss) | true |
