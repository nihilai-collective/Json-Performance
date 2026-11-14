
----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) STATISTICAL TIE | 620.646 | 1.20433 | 606.449ms | 4390 | 40 | 263992 | 6745.6 | 0.700637 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 614.236 | 0.645628 | 728.603ms | 4390 | 80 | 154922 | 6816 | 0.0938086 | 1(Tie) | true |
