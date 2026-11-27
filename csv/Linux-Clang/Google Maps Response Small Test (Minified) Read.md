
----
### Google Maps Response Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1280.97 | 0.0697578 | 1050.49ms | 4390 | 4890 | 25418.3 | 3268.33 | 0.100597 | 4.06084 | 18.1157 | 3.37198 | 0.00223109 | 0.000103321 | 4.63034e-05 | 1(Win) | true |
| simdjson (ondemand) | 1049.88 | 0.133145 | 1128.67ms | 4390 | 640 | 18041.9 | 3987.72 | 0.0101473 | 4.94596 | 20.4005 | 3.53235 | 0.00412514 | 6.26424e-05 | 2.81179e-05 | 2(Loss) | true |
