
----
### Google Maps Response Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2036 | 1.42919 | 620.751ms | 11812 | 80 | 500220 | 5532.8 | 0.0578704 | 1(Win) | true |
| Jsonifier (two-stage) | 1383.95 | 0.432182 | 928.707ms | 11812 | 640 | 791989 | 8139.6 | 1.06785 | 2(Loss) | true |
| simdjson (reflection) | 1094.61 | 0.501433 | 1169.67ms | 11812 | 80 | 213033 | 10291.2 | 1.06851 | 3(Loss) | true |
| Glaze | 1062.63 | 0.187168 | 1147.9ms | 11812 | 2560 | 1.00783e+06 | 10600.9 | 0.377805 | 4(Loss) | true |
| simdjson (ondemand) | 745.105 | 0.543252 | 1686.68ms | 11812 | 160 | 1.07928e+06 | 15118.4 | 0.494945 | 5(Loss) | true |
