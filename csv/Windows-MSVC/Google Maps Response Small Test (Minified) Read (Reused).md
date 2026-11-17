
----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1348.89 | 0.145492 | 369.363ms | 4390 | 80 | 1631.33 | 3103.75 | 0.200965 | 1.81673 | 1(Win) | true |
| Jsonifier (two-stage) | 1054.57 | 0.258267 | 453.688ms | 4390 | 40 | 4205.13 | 3970 | 0.421585 | 2.3271 | 2(Loss) | true |
| Glaze | 970.954 | 0.150226 | 525.421ms | 4390 | 160 | 6713.44 | 4311.88 | 0.276163 | 2.53106 | 3(Loss) | true |
| simdjson (ondemand) | 560.53 | 0.335944 | 797.52ms | 4390 | 1280 | 805891 | 7469.06 | 0.094227 | 4.39963 | 4(Loss) | true |
