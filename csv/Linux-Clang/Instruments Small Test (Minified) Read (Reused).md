
----
### Instruments Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2749.45 | 0.227809 | 901.988ms | 4669 | 640 | 8711.25 | 1619.49 | 0.00636734 | 1.88802 | 7.70165 | 1.52667 | 0.00111473 | 1.37208e-05 | 0 | 1(Win) | true |
| Glaze | 2338.98 | 0.202574 | 926.263ms | 4669 | 1280 | 19035.9 | 1903.69 | 0.0501744 | 2.2226 | 9.35875 | 1.63097 | 0.000794302 | 2.81109e-05 | 6.69308e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 2025.43 | 0.104836 | 957.705ms | 4669 | 4890 | 25974.4 | 2198.4 | 0.120366 | 2.55096 | 10.9349 | 1.8807 | 0.00120194 | 5.64573e-05 | 2.28194e-05 | 3(Loss) | true |
| simdjson (ondemand) | 679.86 | 0.125882 | 1404.68ms | 4669 | 2560 | 174012 | 6549.44 | 0.0946586 | 7.43409 | 30.8385 | 4.34761 | 0.00239152 | 9.83046e-05 | 4.87758e-05 | 4(Loss) | true |
