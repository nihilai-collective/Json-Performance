
----
### Canada Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1796.91 | 0.112019 | 729.282ms | 11579 | 4890 | 231727 | 6145.31 | 0.297185 | 1(Win) | true |
| Jsonifier (two-stage) | 1671.3 | 0.434777 | 779.521ms | 11579 | 320 | 264069 | 6607.2 | 0.0121065 | 2(Loss) | true |
| simdjson (reflection) | 1394.72 | 0.367428 | 914.616ms | 11579 | 1280 | 1.08323e+06 | 7917.4 | 0.0782473 | 3(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 1231.55 | 0.614352 | 1134.62ms | 11579 | 160 | 485502 | 8966.4 | 0.250447 | 4(Tie) | true |
| Glaze STATISTICAL TIE | 1219.83 | 0.161472 | 1015.41ms | 11579 | 1280 | 273495 | 9052.6 | 0.24903 | 4(Tie) | true |
