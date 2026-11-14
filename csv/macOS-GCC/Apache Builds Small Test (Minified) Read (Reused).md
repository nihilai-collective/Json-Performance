
----
### Apache Builds Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2041.74 | 0.503368 | 155.012ms | 2632 | 4890 | 187262 | 1229.38 | 0.0794423 | 1(Win) | true |
| Glaze STATISTICAL TIE | 1802.95 | 1.02139 | 169.263ms | 2632 | 1280 | 258820 | 1392.2 | 0.302594 | 2(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1795.14 | 0.517376 | 171.761ms | 2632 | 4890 | 255916 | 1398.26 | 0.174015 | 2(Tie) | true |
| simdjson (reflection) | 1345.16 | 0.54915 | 226.62ms | 2632 | 1280 | 134405 | 1866 | 0.0856714 | 4(Loss) | true |
| simdjson (ondemand) | 1117.77 | 1.24748 | 252.747ms | 2632 | 320 | 251121 | 2245.6 | 0.177809 | 5(Loss) | true |
