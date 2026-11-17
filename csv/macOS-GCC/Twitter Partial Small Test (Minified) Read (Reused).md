
----
### Twitter Partial Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 3944.97 | 2.62335 | 81.303ms | 2889 | 640 | 214832 | 698.4 | 0.344828 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 3917.81 | 1.2744 | 76.6149ms | 2889 | 4890 | 392761 | 703.241 | 0.503551 | 1(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 3627.01 | 1.32943 | 82.0549ms | 2889 | 4890 | 498695 | 759.624 | 0.897101 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 3567.02 | 2.17601 | 86.4591ms | 2889 | 640 | 180794 | 772.4 | 1.63158 | 3(Tie) | true |
| Glaze | 2425.03 | 0.56785 | 118.465ms | 2889 | 4890 | 203535 | 1136.14 | 0.828667 | 5(Loss) | true |
