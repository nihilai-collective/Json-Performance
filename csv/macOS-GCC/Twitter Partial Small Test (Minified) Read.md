
----
### Twitter Partial Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 3890.38 | 2.34427 | 78.11ms | 2889 | 2560 | 705615 | 708.2 | 0.283206 | 1(Win) | true |
| Jsonifier STATISTICAL TIE | 3574.54 | 0.791831 | 80.2409ms | 2889 | 4890 | 182150 | 770.775 | 0.979254 | 2(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 3572.84 | 0.817099 | 80.3231ms | 2889 | 4890 | 194145 | 771.141 | 0.0572342 | 2(Tie) | true |
| simdjson (ondemand) | 3383.06 | 1.51084 | 84.885ms | 2889 | 1280 | 193787 | 814.4 | 1.9019 | 4(Loss) | true |
| Glaze | 2543.31 | 0.55594 | 116.748ms | 2889 | 2560 | 92852.6 | 1083.3 | 0.0646592 | 5(Loss) | true |
