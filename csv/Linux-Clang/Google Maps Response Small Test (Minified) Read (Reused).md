
----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2731.98 | 0.104935 | 913.756ms | 4390 | 2560 | 6619.91 | 1532.45 | 0.0150624 | 1.90164 | 8.69577 | 1.59751 | 0.00229686 | 3.09653e-05 | 6.22864e-06 | 1(Win) | true |
| Glaze | 2017.72 | 0.0636171 | 967.661ms | 4390 | 4890 | 8520.52 | 2074.94 | 0.0444039 | 2.54992 | 12.3059 | 2.32984 | 0.000597193 | 4.89121e-05 | 1.19718e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1758.07 | 0.0981788 | 997.929ms | 4390 | 2560 | 13993.6 | 2381.37 | 0.0661601 | 2.93388 | 13.9581 | 2.27016 | 0.00352159 | 6.9049e-05 | 2.90967e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1164.84 | 0.0939558 | 1117.1ms | 4390 | 2560 | 29193.1 | 3594.16 | 0.132364 | 4.39354 | 19.0039 | 3.06128 | 0.00378924 | 4.04862e-05 | 4.36005e-06 | 4(Loss) | true |
