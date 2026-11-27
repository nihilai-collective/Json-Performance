
----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1999.65 | 0.26921 | 234.022ms | 4390 | 1280 | 40664.3 | 2093.68 | 0.746317 | 1.22274 | 1(Win) | true |
| Glaze | 1707.57 | 0.135723 | 271.303ms | 4390 | 40 | 442.933 | 2451.8 | 0.378018 | 1.43618 | 2(Loss) | true |
| Jsonifier (two-stage) | 1677.66 | 0.152446 | 268.419ms | 4390 | 4890 | 70772.6 | 2495.52 | 0.543117 | 1.45989 | 3(Loss) | true |
| simdjson (reflection) | 1552.98 | 0.0707501 | 285.659ms | 4390 | 80 | 291.031 | 2695.86 | 0.000463676 | 1.5787 | 4(Loss) | true |
| simdjson (ondemand) | 1317.36 | 0.216755 | 331.369ms | 4390 | 4890 | 232043 | 3178.05 | 0.0190904 | 1.86306 | 5(Loss) | true |
